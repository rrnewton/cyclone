#ifndef TAG_ELIM_H
#define TAG_ELIM_H

#include "smlng.h"

namespace TagElim {
extern struct SynthS {
  bool mt_doc: 1;
  bool no_text: 1; // Spc doesn't count
  bool bold_useless: 1;
  bool bold_seen: 1;
  //  bool emph: 1;
  bool ital_useless: 1;
  bool ital_seen: 1;
  bool strong_useless: 1;
  bool strong_seen: 1;
  bool tt_useless: 1;
  bool tt_seen: 1;
  bool plain: 1;
  bool u1: 1; // invariant: true if u2 is true
  bool u2: 1; // invariant: true if u3 is true
  bool u3: 1;
  bool color: 1;
  bool sz: 1;
  int sizes: 10; // 0 at bit n means n DOES get used as a size
  int colors: 8; // 0 at bit n means n DOES get used as a color
};
extern union Synth {
  struct SynthS s;
  unsigned long long i;
};
typedef union Synth synth_t; // not a pointer
extern $(doc_t, synth_t) up_opt(doc_t);

extern struct ShuffleSynth {
  bool color: 1;
  bool sz: 1;
};
typedef struct ShuffleSynth shuffle_synth_t;

$(doc_t,shuffle_synth_t) up_shuffle(doc_t d);

extern struct UnderSynth {
  unsigned char ulevel;
  unsigned char all_plain; // a boolean -- means ulevel is irrelevant
};
typedef struct UnderSynth under_synth_t;

$(doc_t,under_synth_t) under_elim(doc_t doc);

extern struct DynSynth {
  int num_size_docs;   // how many size docs we'd program over
  int num_color_docs;  // how many color docs we'd program over
  unsigned char only_sizes;  // are there only size docs
  unsigned char only_colors; // are there only color docs
};
typedef struct DynSynth dyn_synth_t;

$(doc_t,dyn_synth_t) dynamic_regions(doc_t doc,
				     bool shift_window,
				     int window_size);

}
#endif
