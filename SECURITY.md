# Security Policy

## Reporting a Vulnerability

If you discover a security vulnerability in SmartEVSE, please report it responsibly through GitHub's private vulnerability reporting feature:

1. Go to the **Security** tab of this repository
2. Click **Report a vulnerability**
3. Fill in the details of the vulnerability

Please **do not** open a public issue for security vulnerabilities.

## What to Report

SmartEVSE is an internet-connected device that controls mains electricity. Security issues of particular concern include:

- Remote code execution via WiFi, MQTT, REST API, or OCPP interfaces
- Authentication bypass on the web interface or RFID system
- Firmware update integrity issues (unsigned or tampered OTA updates)
- Modbus communication spoofing that could affect charging safety
- Denial of service that could leave contactors in an unsafe state
- Information disclosure of WiFi credentials or RFID card data

## Supported Versions

| Version | Supported |
|---------|-----------|
| v3.10.x | Yes |
| < v3.10 | No |

## Response Timeline

- **Acknowledgment**: Within 48 hours
- **Initial assessment**: Within 1 week
- **Fix or mitigation**: Depends on severity, targeting 30 days for critical issues
