string device
uint8 channel
uint8 id
uint8 command_type    # 0: enable, 1: disable, 2: zeroing, 3: set mode ...
uint8 mode_type       # 仅当 command_type = 3 时使用，0: position, 1: velocity 等