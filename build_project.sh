#!/bin/bash

# Get the directory of the current script
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

# Run delete_binaries.sh
echo "Running delete_binaries.sh..."
"$SCRIPT_DIR/delete_binaries.sh"
if [ $? -ne 0 ]; then
    echo "delete_binaries.sh encountered an error. Exiting."
    exit 1
fi

# Run Build.sh for Unreal Engine
echo "Running Unreal Engine Build..."
/mnt/archstoragenvme/UnrealEngine/Engine/Build/BatchFiles/Linux/Build.sh BomberManEditor Linux Development /home/ural/GitHub/BomberMan/BomberMan.uproject -waitmutex
if [ $? -ne 0 ]; then
    echo "Unreal Engine Build encountered an error. Exiting."
    exit 1
fi

echo "All commands executed successfully!"

