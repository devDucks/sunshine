import pytest
import serial

from .helpers import Arduino


@pytest.fixture(scope="session", autouse=True)
def arduino(request):
    yield Arduino()
