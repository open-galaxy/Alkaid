#include "fs.h"
#include "util.h"

namespace alkaid {

namespace fs {

void ReadFileV8(const FunctionCallbackInfo<Value> &args) {
  Isolate *isolate = args.GetIsolate();
  if (args[0]->IsString()) {
    String::Utf8Value path(isolate, args[0]);
    const char* source = ReadFile(*path, NULL);
    args.GetReturnValue().Set(String::NewFromUtf8(isolate, source, NewStringType::kNormal).ToLocalChecked());
  }
}

char* ReadFile(const char* path, unsigned int* file_len_out) {
  FILE *file;
  int e;

  file = fopen(path, "rb");
  if (!file) {
    fprintf(stderr, "Unable to open file %s\n", path);
    return NULL;
  }

  e = fseek(file, 0, SEEK_END);
  if (-1 == e) {
    fprintf(stderr, "Unable to seek file %s\n", path);
    fclose(file);
    return NULL;
  }

  long file_len = ftell(file);
  if (-1 == file_len) {
    fprintf(stderr, "Unable to ftell() file %s\n", path);
    fclose(file);
    return NULL;
  }

  e = fseek(file, 0, SEEK_SET);
  if (-1 == e) {
    fprintf(stderr, "Unable to seek file %s\n", path);
    fclose(file);
    return NULL;
  }

  char* contents = (char*) malloc(file_len + 1);
  if (!contents) {
    fprintf(stderr, "Memory error!\n");
    fclose(file);
    return NULL;
  }

  unsigned long bytes_read = fread(contents, file_len, 1, file);
  if (bytes_read == 0 && ferror(file)) {
    fprintf(stderr, "Read error");
    free(contents);
    fclose(file);
    return NULL;
  }
  fclose(file);

  contents[file_len] = '\0';

  if (file_len_out)
    *file_len_out = file_len + 1;

  return contents;
}

Local<ObjectTemplate> Initialize(Isolate* isolate) {
  Local<ObjectTemplate> fs = ObjectTemplate::New(isolate);

  SET_METHOD(isolate, "readFile", fs, ReadFileV8);

  return fs;
}

} // namespace fs

} // namespace alkaid