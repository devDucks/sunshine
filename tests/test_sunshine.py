import time


def test_malformed_command_no_colon(arduino):
    arduino.write(b"ABC#")
    response = arduino.read_all()
    assert response == b":E1#"


def test_malformed_command_no_hash(arduino):
    arduino.write(b":LOL")
    response = arduino.read_all()
    assert response == b":E2#"


def test_non_existent_command(arduino):
    arduino.write(b":FOO#")
    response = arduino.read_all()
    assert response == b":E3#"


def test_ping_command(arduino):
    arduino.write(b":P#")
    response = arduino.read_all()
    assert response == b":OK#"


def test_version_command(arduino):
    arduino.write(b":V#")
    response = arduino.read_all()
    assert response == b":V001#"


def test_direction_command(arduino):
    arduino.write(b":DR#")
    response = arduino.read_until()
    assert response == b":D1#"
    time.sleep(1.0)

    arduino.write(b":D0#")
    response = arduino.read_until()
    assert response == b":OK#"
    arduino.write(b":DR#")
    response = arduino.read_until()
    assert response == b":D0#"

    time.sleep(1.0)
    # Reset the pull to setup HIGH
    arduino.write(b":D1#")
    response = arduino.read_until()
    assert response == b":OK#"
    arduino.write(b":DR#")
    response = arduino.read_all()
    assert response == b":D1#"
