#!/bin/bash

RULES_FILE="/etc/udev/rules.d/99-usbcan.rules"

if [ "$EUID" -ne 0 ]; then
  echo "请用 root 权限运行此脚本"
  exit 1
fi

echo "请确保目标设备已插入并识别，接下来将自动检测设备信息"

read -p "请输入要绑定的设备符号链接名（例如 ttyUSB_can0）: " DEVNAME

# 通过 dmesg 或 sysfs 找出最近插入的 ACM 设备
# 这里以 ttyACM 设备为例，获取最近插入的 ttyACM 设备节点
DEV_NODE=$(ls -1t /dev/ttyACM* 2>/dev/null | head -n1)

if [ -z "$DEV_NODE" ]; then
  echo "未检测到任何 /dev/ttyACM* 设备，请确认设备已正确插入"
  exit 1
fi

echo "检测到设备节点: $DEV_NODE"

# 通过 udevadm 获取设备属性
UDEV_INFO=$(udevadm info -a -n "$DEV_NODE")

# 提取 idVendor, idProduct, serial
VID=$(echo "$UDEV_INFO" | grep 'ATTRS{idVendor}' | head -n1 | sed -r 's/.*==\"([0-9a-fA-F]+)\"/\1/')
PID=$(echo "$UDEV_INFO" | grep 'ATTRS{idProduct}' | head -n1 | sed -r 's/.*==\"([0-9a-fA-F]+)\"/\1/')
SERIAL=$(echo "$UDEV_INFO" | grep 'ATTRS{serial}' | head -n1 | sed -r 's/.*==\"(.+)\"/\1/')

if [ -z "$VID" ] || [ -z "$PID" ] || [ -z "$SERIAL" ]; then
  echo "未能正确获取设备的 vid, pid 或 serial，终止操作"
  exit 1
fi

echo "检测到设备信息:"
echo "  VID: $VID"
echo "  PID: $PID"
echo "  Serial: $SERIAL"

# 备份已有规则
if [ -f "$RULES_FILE" ]; then
  cp "$RULES_FILE" "${RULES_FILE}.bak.$(date +%s)"
fi

# 删除已有相同serial的规则
sed -i "/ATTRS{serial}==\"$SERIAL\"/d" "$RULES_FILE" 2>/dev/null

# 写入新规则
echo "SUBSYSTEM==\"tty\", ATTRS{idVendor}==\"$VID\", ATTRS{idProduct}==\"$PID\", ATTRS{serial}==\"$SERIAL\", SYMLINK+=\"$DEVNAME\" , MODE=\"0666\", GROUP=\"dialout\"" >> "$RULES_FILE"

echo "规则已写入 $RULES_FILE"

echo "请执行以下命令应用新规则："
echo "  sudo udevadm control --reload-rules"
echo "  sudo udevadm trigger"

echo "完成！请拔插设备确认设备符号链接是否正确创建。"