// Macro that calls a COM method returning HRESULT value.
#define CHK_HR(stmt)        do { hr=(stmt); if (FAILED(hr)) goto CleanUp; } while(0)

// Macro to verify memory allcation.
#define CHK_ALLOC(p)        do { if (!(p)) { hr = E_OUTOFMEMORY; goto CleanUp; } } while(0)

// Macro that releases a COM object if not NULL.
#define SAFE_RELEASE(p)     do { if ((p)) { (p)->Release(); (p) = NULL; } } while(0)

int main(int argc, char * argv[]);

void WriteOutFiles(std::ofstream& outputHeader_file, std::ofstream& outputConfigfile);

void WriteObstaclesFiles(std::ofstream & ObstaclesOutputFile);

void loadDOMGraphics(std::string filename);

void loadDOMConfiguration(std::string filename);
