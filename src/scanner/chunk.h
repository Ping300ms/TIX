struct Chunk
{
  /*
    Stores every tags/content pair of a file.
    Simplifies greatly the work of the extractor.
  */
  char* tags;
  char* content;
  struct Chunk* next;
  /*
    Chunks are in the form of a linked list to simplify their allocation in
    the scanner.
  */
};

