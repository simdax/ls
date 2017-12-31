#include "ft_ls.h"

int		read_dir(char *file)
{
  DIR  		*dir;
  struct dirent	*dir_inf;
  char		*tmp_name;
  char		**argv2;
  t_list	*list;

  list = NULL;
  if (!(dir = opendir(file)))
    {
      printf("%s : ", file); fflush(stdout);
      perror("erreur d'ouverture ");
      return (errno);
    }
  else
    {
      while (dir_inf = readdir(dir))
        {
          ft_lstadd(&list,
                    ft_lstnew(dir_inf->d_name,
                              strlen(dir_inf->d_name))
                    );
          //print_dirent(dir_inf);
          if ( dir_inf->d_type == DT_DIR &&
               (strcmp("..", dir_inf->d_name)) &&
               (strcmp(".", dir_inf->d_name)))
            {
              tmp_name = cat_filename(file, dir_inf->d_name);
              //              read_dir(tmp_name);
              free(tmp_name);
            }
        }
      closedir(dir);
      ft_lstiter(list, ({
            void _(t_list *el){
              printf("%s\n", el->content);
              fflush(stdout);
            }
            _;
            }));
      return (0);
    }  
}
