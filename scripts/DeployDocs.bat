pip install requests

python scripts/SetupDoxygen.py

vendor\\doxygen\\doxygen

git clone --single-branch --branch gh-pages https://github.com/Jaysmito101/TerraForge3D ./ghpages

xcopy Docs\\html\\ ghpages\\documentation\\  /E /H /C /R /Q /Y