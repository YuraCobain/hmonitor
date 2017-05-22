file(REMOVE_RECURSE
  "libhm_drivers.pdb"
  "libhm_drivers.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/hm_drivers.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
