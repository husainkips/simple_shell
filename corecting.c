int change_directory(data_shell *datash) {
    char *dir = datash->args[1];

    if (dir == NULL || is_home_directory(dir) || is_double_dash(dir)) {
        change_directory_to_home(datash);
        return 1;
    }

   if  (is_previous_directory(dir)) {
        change_directory_to_previous(datash);
        return 1;
    }

   if (is_dot_directory(dir)) {
        change_directory_to_dot(datash);
        return 1;
    }
