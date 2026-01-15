#!/bin/bash
# setup_linux.sh

echo "Installing system-level dependencies..."
sudo apt-get update
sudo apt-get install -y build-essential hyperfine python3-venv python3-pip

# --- Python Virtual Environment Setup ---
echo "Creating Python virtual environment in ./venv..."
python3 -m venv venv

# Upgrade pip and install from requirements.txt
echo "Installing Python dependencies from requirements.txt..."
./venv/bin/pip install --upgrade pip
./venv/bin/pip install -r requirements.txt

echo "✅ Environment ready!"