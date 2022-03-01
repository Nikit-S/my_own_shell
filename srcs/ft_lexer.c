#include "../incs/includes.h"

static char	*init_lexer(char ***tokens, char **str, char **word)
{
	char	*temp;

	(*tokens) = malloc(sizeof(char *) * 1);
	(*tokens)[0] = NULL;
	temp = ft_strdup(skip_space(*str, " "));
	free(*str);
	*str = ft_strdup(temp);
	free(temp);
	*word = NULL;
	return (temp);
}

static int	add_word(char ***tokens, char **word)
{
	char	**tokens2;

	tokens2 = ft_arr_push(*tokens, *word);
	free_split(*tokens);
	*tokens = tokens2;
	free(*word);
	*word = NULL;
	return (0);
}

static int	add_sym(char ***tokens, char *temp, int *i)
{
	char	*word;

	word = NULL;
	if (temp[*i] == ' ')
		return (0);
	if (ft_strchr("><", temp[*i]) && temp[*i + 1] && temp[*i + 1] == temp[*i])
	{
		(*i)++;
		add_char(&word, temp[*i]);
		add_char(&word, temp[*i]);
	}
	else
		add_char(&word, temp[*i]);
	add_word(tokens, &word);
	return (0);
}

static void	hack(char *str, int *qt, char **word, char ***tokens)
{
	int	i;

	i = 0;
	while (1)
	{
		if ((!ft_strchr("|<> ", str[i]) && !(*qt)) || (*qt))
			add_char(word, str[i]);
		if (ft_strchr("\"\'", str[i]))
		{
			if ((*qt) == 0)
				(*qt) = str[i];
			else if (*qt == str[i])
				(*qt) = 0;
		}
		if (ft_strchr(" |<>", str[i]) && !(*qt))
		{
			if (ft_strlen(*word) != 0)
				add_word(tokens, word);
			if (str[i])
				add_sym(tokens, str, &i);
		}
		if (str[i] == 0)
			break ;
		i++;
	}
}

char	**ft_lexer(char *str)
{
	char	**tokens;
	char	*word;
	int		qt;

	if (!str || ft_strlen(skip_space(str, " ")) == 0)
		return (NULL);
	init_lexer(&tokens, &str, &word);
	qt = 0;
	hack(str, &qt, &word, &tokens);
	if (word)
		free(word);
	return (tokens);
}
