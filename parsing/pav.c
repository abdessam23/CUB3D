int check_map(char *s)
{
    char *str;
    int count = 0;
    int line;
    if (!*s)
        return 0;
    
    str = read_line(s);
    if (*str)
    {
       while (*str && ft_whitespace(*str))
            str++;
        
        if (ft_identif(*str))
        {
            while (*str && *str != '\n')
                str++;
            while (*str && ft_whitespace(*str)) str++; 
            if (ft_identif(*str))
            {
                while (*str && *str != '\n')
                    str++;
                while (*str && ft_whitespace(*str)) str++;                           
                if (ft_identif(*str))
                {
                    while (*str && *str != '\n')
                        str++;
                    while (*str && ft_whitespace(*str)) str++;
                    if (ft_identif(*str))
                    {
                        while (*str && *str != '\n')
                            str++;
                        while (*str && ft_whitespace(*str)) str++;
                        if (ft_identif(*str))
                        {
                            while (*str && *str != '\n')
                                str++;
                            while (*str && ft_whitespace(*str)) str++;
                            if (ft_identif(*str))
                            {
                                while (*str && *str != '\n')
                                str++;
                                while (*str && ft_whitespace(*str)) str++;
                                if(*str == '1')
                                    return 1;
                                else
                                    return 0;
                            }
                            else
                                return 0;
                        }
                        else
                                return 0;
                    }
                    else
                                return 0;   
                }
                else
                                return 0; 
            }
            
        }
        else
            return 0;
    }
    return 0;
}


int check_map_recursive(char *str)
{
    // Base case 1: end of string
    if (*str == '\0')
        return 0;

    // Skip whitespace characters
    while (*str && ft_whitespace(*str))
        str++;

    // Base case 2: If not a valid identifier at current position
    if (!ft_identif(*str))
        return 0;

    // Process the identifier (move to the next part after the identifier)
    while (*str && *str != '\n')
        str++;

    // Skip any following whitespace
    while (*str && ft_whitespace(*str))
        str++;

    // If we've reached the end of the string, return 1 (success)
    if (*str == '\0')
        return 1;

    // Recursive case: continue checking the next identifier
    return check_map_recursive(str);
}

int check_map(char *s)
{
    // Start the recursion by calling on the initial string
    if (*s == '\0')
        return 0;

    // Call the recursive function with the initial string
    return check_map_recursive(s);
}
