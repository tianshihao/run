function(auto_main cpp_file)
  get_filename_component(exec_name ${cpp_file} NAME_WE)
  file(READ ${cpp_file} file_content)

  if(file_content STREQUAL "")
    file(WRITE ${cpp_file} "namespace run::playground::${exec_name} {\n\n} // namespace run::playground::${exec_name}\n\nint main() {\n    return 0;\n}\n")
  endif()
endfunction()
