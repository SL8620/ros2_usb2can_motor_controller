from setuptools import find_packages
from setuptools import setup

setup(
    name='motor_interfaces',
    version='0.1.0',
    packages=find_packages(
        include=('motor_interfaces', 'motor_interfaces.*')),
)
