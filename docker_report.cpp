/**
 * Docker Report - A C++ utility for Docker container and image reporting
 * 
 * This program demonstrates C++ programming concepts while providing
 * useful Docker reporting functionality. It showcases:
 * - System command execution
 * - String processing and parsing
 * - Object-oriented programming
 * - Error handling
 * - File I/O operations
 * 
 * Author: Generated for GitHub Skills Tutorial
 * Purpose: Educational demonstration of C++ programming with Docker integration
 */

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <memory>
#include <map>
#include <iomanip>

class DockerReporter {
private:
    // Structure to hold container information
    struct ContainerInfo {
        std::string id;
        std::string name;
        std::string image;
        std::string status;
        std::string ports;
        
        ContainerInfo(const std::string& id = "", const std::string& name = "", 
                     const std::string& image = "", const std::string& status = "",
                     const std::string& ports = "") 
            : id(id), name(name), image(image), status(status), ports(ports) {}
    };
    
    // Structure to hold image information
    struct ImageInfo {
        std::string repository;
        std::string tag;
        std::string imageId;
        std::string created;
        std::string size;
        
        ImageInfo(const std::string& repo = "", const std::string& tag = "",
                 const std::string& id = "", const std::string& created = "",
                 const std::string& size = "")
            : repository(repo), tag(tag), imageId(id), created(created), size(size) {}
    };
    
    std::vector<ContainerInfo> containers;
    std::vector<ImageInfo> images;
    
    /**
     * Execute a system command and return its output
     * @param command The command to execute
     * @return The command output as a string
     */
    std::string executeCommand(const std::string& command) {
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);
        
        if (!pipe) {
            throw std::runtime_error("Failed to execute command: " + command);
        }
        
        char buffer[128];
        while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
            result += buffer;
        }
        
        return result;
    }
    
    /**
     * Check if Docker is available on the system
     * @return true if Docker is available, false otherwise
     */
    bool isDockerAvailable() {
        try {
            std::string output = executeCommand("docker --version 2>/dev/null");
            return !output.empty();
        } catch (const std::exception&) {
            return false;
        }
    }
    
    /**
     * Parse Docker container information from docker ps output
     */
    void parseContainers() {
        containers.clear();
        
        try {
            std::string output = executeCommand("docker ps -a --format \"table {{.ID}}\\t{{.Names}}\\t{{.Image}}\\t{{.Status}}\\t{{.Ports}}\" 2>/dev/null");
            std::istringstream stream(output);
            std::string line;
            
            // Skip header line
            if (std::getline(stream, line)) {
                while (std::getline(stream, line)) {
                    if (line.empty()) continue;
                    
                    std::istringstream lineStream(line);
                    std::string id, name, image, status, ports;
                    
                    if (std::getline(lineStream, id, '\t') &&
                        std::getline(lineStream, name, '\t') &&
                        std::getline(lineStream, image, '\t') &&
                        std::getline(lineStream, status, '\t')) {
                        
                        std::getline(lineStream, ports, '\t');
                        containers.emplace_back(id, name, image, status, ports);
                    }
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error parsing containers: " << e.what() << std::endl;
        }
    }
    
    /**
     * Parse Docker image information from docker images output
     */
    void parseImages() {
        images.clear();
        
        try {
            std::string output = executeCommand("docker images --format \"table {{.Repository}}\\t{{.Tag}}\\t{{.ID}}\\t{{.CreatedAt}}\\t{{.Size}}\" 2>/dev/null");
            std::istringstream stream(output);
            std::string line;
            
            // Skip header line
            if (std::getline(stream, line)) {
                while (std::getline(stream, line)) {
                    if (line.empty()) continue;
                    
                    std::istringstream lineStream(line);
                    std::string repo, tag, id, created, size;
                    
                    if (std::getline(lineStream, repo, '\t') &&
                        std::getline(lineStream, tag, '\t') &&
                        std::getline(lineStream, id, '\t') &&
                        std::getline(lineStream, created, '\t') &&
                        std::getline(lineStream, size, '\t')) {
                        
                        images.emplace_back(repo, tag, id, created, size);
                    }
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Error parsing images: " << e.what() << std::endl;
        }
    }

public:
    /**
     * Generate a comprehensive Docker report
     */
    void generateReport() {
        std::cout << "=================================================\n";
        std::cout << "           DOCKER SYSTEM REPORT\n";
        std::cout << "=================================================\n\n";
        
        // Check Docker availability
        if (!isDockerAvailable()) {
            std::cout << "❌ Docker is not available on this system.\n";
            std::cout << "Please install Docker to use this reporting tool.\n";
            return;
        }
        
        std::cout << "✅ Docker is available on this system.\n\n";
        
        // Parse Docker data
        parseContainers();
        parseImages();
        
        // Display container report
        displayContainerReport();
        
        // Display image report
        displayImageReport();
        
        // Display system summary
        displaySystemSummary();
        
        // Generate report file
        generateReportFile();
    }
    
    /**
     * Display detailed container information
     */
    void displayContainerReport() {
        std::cout << "📦 CONTAINER REPORT\n";
        std::cout << "-------------------------------------------------\n";
        
        if (containers.empty()) {
            std::cout << "No containers found.\n\n";
            return;
        }
        
        std::cout << std::left << std::setw(12) << "ID" 
                  << std::setw(20) << "NAME" 
                  << std::setw(20) << "IMAGE" 
                  << std::setw(15) << "STATUS" 
                  << "PORTS\n";
        std::cout << std::string(80, '-') << "\n";
        
        for (const auto& container : containers) {
            std::cout << std::left << std::setw(12) << container.id.substr(0, 11)
                      << std::setw(20) << container.name.substr(0, 19)
                      << std::setw(20) << container.image.substr(0, 19)
                      << std::setw(15) << container.status.substr(0, 14)
                      << container.ports << "\n";
        }
        std::cout << "\n";
    }
    
    /**
     * Display detailed image information
     */
    void displayImageReport() {
        std::cout << "🖼️  IMAGE REPORT\n";
        std::cout << "-------------------------------------------------\n";
        
        if (images.empty()) {
            std::cout << "No images found.\n\n";
            return;
        }
        
        std::cout << std::left << std::setw(25) << "REPOSITORY" 
                  << std::setw(15) << "TAG" 
                  << std::setw(12) << "IMAGE ID" 
                  << std::setw(10) << "SIZE\n";
        std::cout << std::string(70, '-') << "\n";
        
        for (const auto& image : images) {
            std::cout << std::left << std::setw(25) << image.repository.substr(0, 24)
                      << std::setw(15) << image.tag.substr(0, 14)
                      << std::setw(12) << image.imageId.substr(0, 11)
                      << image.size << "\n";
        }
        std::cout << "\n";
    }
    
    /**
     * Display system summary statistics
     */
    void displaySystemSummary() {
        std::cout << "📊 SYSTEM SUMMARY\n";
        std::cout << "-------------------------------------------------\n";
        
        int runningContainers = 0;
        int stoppedContainers = 0;
        
        for (const auto& container : containers) {
            if (container.status.find("Up") != std::string::npos) {
                runningContainers++;
            } else {
                stoppedContainers++;
            }
        }
        
        std::cout << "Total Containers: " << containers.size() << "\n";
        std::cout << "  - Running: " << runningContainers << "\n";
        std::cout << "  - Stopped: " << stoppedContainers << "\n";
        std::cout << "Total Images: " << images.size() << "\n\n";
        
        // Display Docker version info
        try {
            std::string dockerVersion = executeCommand("docker --version 2>/dev/null");
            std::cout << "Docker Version: " << dockerVersion;
        } catch (const std::exception&) {
            std::cout << "Docker Version: Unable to determine\n";
        }
        
        std::cout << "\n";
    }
    
    /**
     * Generate a detailed report file
     */
    void generateReportFile() {
        const std::string filename = "docker_report.txt";
        std::ofstream reportFile(filename);
        
        if (!reportFile.is_open()) {
            std::cerr << "❌ Unable to create report file: " << filename << std::endl;
            return;
        }
        
        reportFile << "Docker System Report\n";
        reportFile << "Generated on: " << __DATE__ << " " << __TIME__ << "\n";
        reportFile << "=================================================\n\n";
        
        reportFile << "CONTAINERS (" << containers.size() << " total):\n";
        for (const auto& container : containers) {
            reportFile << "- " << container.name << " (" << container.id << ")\n";
            reportFile << "  Image: " << container.image << "\n";
            reportFile << "  Status: " << container.status << "\n";
            if (!container.ports.empty()) {
                reportFile << "  Ports: " << container.ports << "\n";
            }
            reportFile << "\n";
        }
        
        reportFile << "IMAGES (" << images.size() << " total):\n";
        for (const auto& image : images) {
            reportFile << "- " << image.repository << ":" << image.tag << "\n";
            reportFile << "  ID: " << image.imageId << "\n";
            reportFile << "  Size: " << image.size << "\n";
            reportFile << "  Created: " << image.created << "\n\n";
        }
        
        reportFile.close();
        std::cout << "📄 Detailed report saved to: " << filename << "\n\n";
    }
};

/**
 * Display usage information
 */
void displayUsage(const std::string& programName) {
    std::cout << "Usage: " << programName << " [OPTIONS]\n\n";
    std::cout << "Docker Report - A C++ utility for Docker system reporting\n\n";
    std::cout << "Options:\n";
    std::cout << "  -h, --help     Show this help message\n";
    std::cout << "  -v, --version  Show version information\n\n";
    std::cout << "This program generates a comprehensive report of your Docker environment,\n";
    std::cout << "including containers, images, and system statistics.\n\n";
    std::cout << "Examples:\n";
    std::cout << "  " << programName << "           # Generate full Docker report\n";
    std::cout << "  " << programName << " --help    # Show this help\n\n";
}

/**
 * Display version information
 */
void displayVersion() {
    std::cout << "Docker Report v1.0.0\n";
    std::cout << "A C++ utility for Docker system reporting\n";
    std::cout << "Built for educational purposes in GitHub Skills tutorial\n\n";
}

/**
 * Main function - Entry point of the program
 */
int main(int argc, char* argv[]) {
    // Handle command line arguments
    if (argc > 1) {
        std::string option = argv[1];
        if (option == "-h" || option == "--help") {
            displayUsage(argv[0]);
            return 0;
        } else if (option == "-v" || option == "--version") {
            displayVersion();
            return 0;
        } else {
            std::cerr << "Unknown option: " << option << std::endl;
            std::cerr << "Use --help for usage information.\n";
            return 1;
        }
    }
    
    try {
        // Create Docker reporter instance and generate report
        DockerReporter reporter;
        reporter.generateReport();
        
        std::cout << "Report generation completed successfully! ✅\n";
        return 0;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "❌ An unknown error occurred." << std::endl;
        return 1;
    }
}