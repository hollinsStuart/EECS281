template <typename T>
void genPerms(vector<T> &path, size_t permLength) {
  if (permLength == path.size()) {
  // Do something with the path
    return;
  }  // if ..complete path

  if (!promising(path, permLength)) {
    return;
  }  // if ..not promising

  for (size_t i = permLength; i < path.size(); ++i) {
    swap(path[permLength], path[i]);
    genPerms(path, permLength + 1);
    swap(path[permLength], path[i]);
  }  // for ..unpermuted elements
}  // genPerms()
