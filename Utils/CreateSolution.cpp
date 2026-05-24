#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

#ifdef _WIN32
#include <direct.h>
#define MKDIR(path) _mkdir(path.c_str())
#else
#include <sys/stat.h>
#include <unistd.h>
#define MKDIR(path) mkdir(path.c_str(), 0777)
#endif

using namespace std;

string slugify(string text) {
   text = regex_replace(text, regex("[^a-zA-Z0-9\\s-]"), "");
   text = regex_replace(text, regex("[\\s-]+"), "-");
   if (!text.empty() && text.front() == '-') text.erase(0, 1);
   if (!text.empty() && text.back() == '-') text.pop_back();
   return text;
}

int main(int argc, char* argv[]) {
   if (argc >= 2 && string(argv[1]) == "clear") {
      ofstream last_sol_file(".dev/last_solution.txt", ios::trunc);
      if (last_sol_file.is_open()) {
         last_sol_file.close();
      }
      return 0;
   }
   if (argc < 3) return 1;

   string difficulty = argv[1];
   string full_name = "";
   for (int i = 2; i < argc; ++i) {
      full_name += string(argv[i]) + (i == argc - 1 ? "" : " ");
   }

   smatch match;
   regex re("^(\\d+)\\.?\\s*(.*)");
   string num, title;

   if (regex_search(full_name, match, re)) {
      num = match[1];
      title = match[2];
   } else {
      cerr << "Error: Invalid format. Expected 'Number. Title'" << endl;
      return 1;
   }

   string folder_name = "[" + num + "]-" + slugify(title);
   string target_dir = difficulty + "/" + folder_name;

   if (MKDIR(target_dir) != 0) {
      cerr << "Error: Could not create directory or it already exists!" << endl;
      return 1;
   }

   ofstream cpp_file(target_dir + "/Solution.cpp");
   cpp_file << "#include \"../../Utils/utils.h\"\n\nusing namespace std;\n\nclass Solution {\npublic:\n   // TODO: Implement\n};\n\nint main() {\n\n   return 0;\n}\n";
   cpp_file.close();

   ofstream md_file(target_dir + "/Design.md");
   md_file << "# Tư duy thiết kế: " << title << "\n\n## Vấn đề\n\n---\n\n## Giải pháp\n\n---\n\n## Tại sao tối ưu?\n\n---\n\n**Tổng kết:**\n";
   md_file.close();

   ifstream sol_file_in("SOLUTIONS.md");
   vector<string> lines;
   string line;
   if (sol_file_in.is_open()) {
      while (getline(sol_file_in, line)) {
         lines.push_back(line);
      }
      sol_file_in.close();
   }

   string new_line = "- [" + num + ". " + title + "](./" + difficulty + "/" + folder_name + ")";
   int new_num = stoi(num);

   string section_header = "## " + difficulty;
   int section_start = -1;
   int section_end = -1;

   for (size_t i = 0; i < lines.size(); ++i) {
      if (lines[i] == section_header) {
         section_start = i;
      } else if (section_start != -1 && section_end == -1 && lines[i].rfind("## ", 0) == 0) {
         section_end = i;
      }
   }
   if (section_start != -1 && section_end == -1) {
      section_end = lines.size();
   }

   bool inserted = false;
   regex entry_re("^- \\[(\\d+)\\.");
   smatch entry_match;

   if (section_start != -1) {
      int insert_pos = section_end;
      for (int i = section_start + 1; i < section_end; ++i) {
         string current_line = lines[i];
         if (regex_search(current_line, entry_match, entry_re)) {
            int existing_num = stoi(entry_match[1]);
            if (new_num < existing_num) {
               insert_pos = i;
               break;
            }
         }
      }
      lines.insert(lines.begin() + insert_pos, new_line);
      inserted = true;
   }

   ofstream sol_file_out("SOLUTIONS.md");
   if (inserted) {
      for (size_t i = 0; i < lines.size(); ++i) {
         sol_file_out << lines[i] << "\n";
      }
   } else {
      for (size_t i = 0; i < lines.size(); ++i) {
         sol_file_out << lines[i] << "\n";
      }
      sol_file_out << "\n" << section_header << "\n\n" << new_line << "\n";
   }
   sol_file_out.close();

   ofstream last_sol_file(".dev/last_solution.txt");
   if (last_sol_file.is_open()) {
      last_sol_file << title;
      last_sol_file.close();
   }

   cout << "Successfully created: " << target_dir << endl;

   return 0;
}
