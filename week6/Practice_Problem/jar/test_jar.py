from jar import Jar
import pytest


def test_init():
    jar1 = Jar()
    jar2 = Jar(15)
    assert jar1.capacity == 12
    assert jar2.capacity == 15


def test_str():
    jar = Jar()
    assert str(jar) == ""
    jar.deposit(1)
    assert str(jar) == "🍪"
    jar.deposit(11)
    assert str(jar) == "🍪🍪🍪🍪🍪🍪🍪🍪🍪🍪🍪🍪"


def test_deposit():
    jar3 = Jar()
    jar3.deposit(1)
    assert jar3.size == 1
    jar3.deposit(11)
    assert jar3.size == 12
    with pytest.raises(ValueError):
        jar3.deposit(1)


def test_withdraw():
    jar4 = Jar()
    jar4.deposit(2)
    jar4.withdraw(1)
    jar4.size == 1
    with pytest.raises(ValueError):
        jar4.withdraw(2)
