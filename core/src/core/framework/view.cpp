#include <core/framework/view.h>
#include <core/framework/framework.h>

namespace vortex {
namespace core {
namespace framework {

view::view(framework* framework) : framework_(framework) {
}

void view::output() {
  // parse_template();

  respond();
}

void view::respond() {
  framework_->response_->body() = rendered_;
}

void view::echo(std::string contents) {
  rendered_ += contents;
}

void view::clear() {
  framework_->response_->body() = "";
  rendered_.clear();
}

void view::finish() {
  template_.clear();
  page_.clear();
  respond();
}

std::string view::parse(std::string code) {
  std::string rendered;

  enum grabbing_stage {
    String, Script, Echo, Comment
  };

  std::string script_code;
  grabbing_stage stage = String;

  for (size_t i = 0; i < code.length(); ++i) {
    char current = code[i];

    if (stage == grabbing_stage::String) {
      if (current == '{') {
        char next = code[i + 1];

        if (next == '{') {
          stage = grabbing_stage::Script;
          script_code.clear();
          ++i;
        } else if (next == '=') {
          stage = grabbing_stage::Echo;
          script_code.clear();
          ++i;
        } else if (next == '#') {
          stage = grabbing_stage::Comment;
          script_code.clear();
          ++i;
        } else if (next == '\\') {
          rendered += current;
          i++;
        } else {
          rendered += current;
        }
      } else {
        rendered += current;
      }
    } else if (stage == grabbing_stage::Script) {
      if (current == '}') {
        char next = code[i + 1];

        if (next == '}') {
          // TODO: Execute script

          script_code.clear();

          stage = grabbing_stage::String;
          ++i;

          if (code[i + 2] == '\n') {
            ++i;
          }
        } else if (next == '\\') {
          script_code += current;
          ++i;
        } else {
          script_code += current;
        }
      } else {
        script_code += current;
      }
    } else if (stage == grabbing_stage::Echo) {
      if (current == '=') {
        char next = code[i + 1];

        if (next == '}') {
          // TODO: Get script result as string

          script_code.clear();

          stage = grabbing_stage::String;
          ++i;

          if (code[i + 2] == '\n') {
            ++i;
          }
        } else if (next == '\\') {
          script_code += current;
          ++i;
        } else {
          script_code += current;
        }
      } else {
        script_code += current;
      }
    } else if (stage == grabbing_stage::Comment) {
      if (current == '#') {
        char next = code[i + 1];

        if (next == '}') {
          stage = grabbing_stage::String;
          ++i;

          if (code[i + 2] == '\n') {
            ++i;
          }
        } else if (next == '\\') {
          ++i;
        }
      }
    }
  }

  return rendered;
}

}  // namespace framework
}  // namespace core
}  // namespace vortex
