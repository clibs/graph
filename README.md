# graph

Simple (directed) graph library.

__NOTE__: This library is currently incomplete. Just pushed it up to save the work. Feel free to test it, but please hold off any contributions for a moment, until I push the rest of the code, so we don't step on each other's toes.

## Usage.

__TODO__.

## TODO.

- Write some damn good documentation!
- Write some more damn good documentation!!!
- Given that `graph_vertex_t` and `graph_edge_t` only live in memory, I will be refactoring them to use their memory addresses as their `id`s instead. This will get rid of the unnecessary memory use. This also means you will no longer be limited to `uint32_t` of vertices and `uint64_t` of edges, but only the available memory on the heap. Also, see the "__Notes!__" section below.
- Fight a bear.
- Add support for adjacency matrices.

## Notes!

- Please, do not rely on the ABI yet ... things are changing, so the ABI will *likely* change a few times before it's somewhat stable. The API, however, while not guaranteed, will most likely only get better, without breaking backwards compatibility.

## Author.

__[Jonathan Barronville](http://乔纳森.com "http://乔纳森.com")__

## Contributors.

No contributors yet.

## License.

See "__/LICENSE__".
