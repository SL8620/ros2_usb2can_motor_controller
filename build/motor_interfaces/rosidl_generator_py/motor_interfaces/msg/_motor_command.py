# generated from rosidl_generator_py/resource/_idl.py.em
# with input from motor_interfaces:msg/MotorCommand.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_MotorCommand(type):
    """Metaclass of message 'MotorCommand'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('motor_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'motor_interfaces.msg.MotorCommand')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__motor_command
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__motor_command
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__motor_command
            cls._TYPE_SUPPORT = module.type_support_msg__msg__motor_command
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__motor_command

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class MotorCommand(metaclass=Metaclass_MotorCommand):
    """Message class 'MotorCommand'."""

    __slots__ = [
        '_device',
        '_channel',
        '_id',
        '_command_type',
        '_mode_type',
    ]

    _fields_and_field_types = {
        'device': 'string',
        'channel': 'uint8',
        'id': 'uint8',
        'command_type': 'uint8',
        'mode_type': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.device = kwargs.get('device', str())
        self.channel = kwargs.get('channel', int())
        self.id = kwargs.get('id', int())
        self.command_type = kwargs.get('command_type', int())
        self.mode_type = kwargs.get('mode_type', int())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.device != other.device:
            return False
        if self.channel != other.channel:
            return False
        if self.id != other.id:
            return False
        if self.command_type != other.command_type:
            return False
        if self.mode_type != other.mode_type:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def device(self):
        """Message field 'device'."""
        return self._device

    @device.setter
    def device(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'device' field must be of type 'str'"
        self._device = value

    @property
    def channel(self):
        """Message field 'channel'."""
        return self._channel

    @channel.setter
    def channel(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'channel' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'channel' field must be an unsigned integer in [0, 255]"
        self._channel = value

    @property  # noqa: A003
    def id(self):  # noqa: A003
        """Message field 'id'."""
        return self._id

    @id.setter  # noqa: A003
    def id(self, value):  # noqa: A003
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'id' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'id' field must be an unsigned integer in [0, 255]"
        self._id = value

    @property
    def command_type(self):
        """Message field 'command_type'."""
        return self._command_type

    @command_type.setter
    def command_type(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'command_type' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'command_type' field must be an unsigned integer in [0, 255]"
        self._command_type = value

    @property
    def mode_type(self):
        """Message field 'mode_type'."""
        return self._mode_type

    @mode_type.setter
    def mode_type(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'mode_type' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'mode_type' field must be an unsigned integer in [0, 255]"
        self._mode_type = value
