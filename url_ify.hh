#pragma once

// find where the pads start
size_t size_pads(const char* str, size_t len) {
  size_t pads = 1;  // count ending null
  for (size_t i = len - 2; i >= 0; --i) {
    if (str[i] == ' ') {
      ++pads;
    } else {
      break;
    }
  }
  return pads;
}

// change space to %20 in place, assuming len has enough space padded for correct result
// also assuming it cannot end with space (otherwise it'd be complicated to see from where the pads are)

// with temporary buffer, n time, n space
void url_ify1(char* str, size_t len) {
  std::vector<char> placeholder;
  size_t pads = size_pads(str, len);

  // put result in placeholder
  for (size_t i = 0; i < len - pads; ++i) {
    if (str[i] == ' ') {
      placeholder.insert(placeholder.end(), {'%', '2', '0'});
    } else {
      placeholder.push_back(str[i]);
    }
  }

  // copy result back to buffer. no need to touch the last terminating null.
  for (size_t i = 0; i < placeholder.size(); ++i) {
    str[i] = placeholder[i];
  }
}

// in place replacements, n^2 time, constant space
void url_ify2(char* str, size_t len) {
  for (size_t i = 0; i < len; ++i) {
    if (str[i] == ' ') {
      for (size_t r = len - 2; r > i + 1; --r) {  // skip terminating null
        str[r] = str[r - 2];
      }
      str[i] = '%';
      str[++i] = '2';
      str[++i] = '0';
    }
  }
}

// in place replacements with 2 indices, n time, constant space
void url_ify3(char* str, size_t len) {
  size_t pads = size_pads(str, len);

  int m = len - pads - 1;
  for (int r = len - 2; r >= 0; --r, --m) {
    if (str[m] == ' ') {
      str[r] = '0';
      str[--r] = '2';
      str[--r] = '%';
    } else {
      str[r] = str[m];
    }
  }
}
