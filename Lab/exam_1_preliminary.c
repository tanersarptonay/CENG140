#include <stdio.h>

float try_btc = 0.0555;
float btc_try = 18.0180;
float try_eth = 0.0833;
float eth_try = 12.0048;
float btc_eth = 1.5001;
float eth_btc = 0.6666;

int main()
{
    int running = 1, lame_money, index, error=0;
    float money, bal_try=0., bal_btc=0., bal_eth=0.;
    float loss, perm_loss, exp_gain, gain=-100.01, temp_gain;
    char op_code, cur, b_cur, s_cur, perm_cur;
    
    
    while (running)
    {
        scanf(" %c", &op_code);
        
        switch (op_code)
        {
            case 'T':
                scanf(" %f", &bal_try);
                break;
                
            case 'Q':
                printf("Bye...\n");
                running = 0;
                break;
            
            case 'R':
                printf("Our account holds %.2f TRY", bal_try);
                if (bal_btc != 0.00) printf(" | %.2f BTC", bal_btc);
                if (bal_eth != 0.00) printf(" | %.2f ETH", bal_eth);
                printf(".\n");
                break;
            
            case 'D':
                scanf(" %c", &cur);
                scanf(" %f", &money);
                if (cur=='T') bal_try+=money;
                else if (cur=='B') bal_btc+=money;
                else if (cur=='E') bal_eth+=money;
                else printf("Error:  Operation could not be completed.\n");
                break;
            
            case 'W':
                scanf(" %c", &cur);
                scanf(" %f", &money);
                switch (cur)
                {
                    case 'T':
                        if (bal_try >= money) bal_try-=money;
                        else printf("Error: Insufficient funds.\n");
                        break;
                    case 'B':
                        if (bal_btc >= money) bal_btc-=money;
                        else printf("Error: Insufficient funds.\n");
                        break;
                    case 'E':
                        if (bal_eth >= money) bal_eth-=money;
                        else printf("Error: Insufficient funds.\n");
                        break;
                    default:
                        printf("Error:  Operation could not be completed.\n");
                        break;
                }
                break;
            
            case 'X':
                scanf(" %c", &s_cur);
                scanf(" %f", &money);
                scanf(" %c", &b_cur);
    
                switch (s_cur)
                {
                    case 'T':
                        if (b_cur=='B')
                        {
                            if (bal_try >= money)
                            {
                                bal_btc += money*try_btc;
                                bal_try -= money;
                                printf("You have successfully bought %.2f BTC.\n", money*try_btc);
                            }
                            else
                            {
                                lame_money = bal_try * try_btc;
                                bal_try -= (lame_money * btc_try);
                                bal_btc += lame_money;
                                printf("This amount is too much, you have successfully bought %.2f BTC.\n", (float)lame_money);
                            }
                        }
                        else if (b_cur=='E')
                        {
                            if (bal_try >= money)
                            {
                                bal_eth += money*try_eth;
                                bal_try -= money;
                                printf("You have successfully bought %.2f ETH.\n", money*try_eth);
                            }
                            else
                            {
                                lame_money = bal_try * try_eth;
                                bal_try -= (lame_money * eth_try);
                                bal_eth += lame_money;
                                printf("This amount is too much, you have successfully bought %.2f ETH.\n", (float)lame_money);
                            }
                        }
                        else printf("Error: Operation could not be completed.\n");
                        break;
                    
                    
                    case 'B':
                        if (b_cur=='T')
                        {
                            if (bal_btc >= money)
                            {
                                bal_try += money*btc_try;
                                bal_btc -= money;
                                printf("You have successfully bought %.2f TRY.\n", money*btc_try);
                            }
                            else
                            {
                                lame_money = bal_btc * btc_try;
                                bal_btc -= (lame_money * try_btc);
                                bal_try += lame_money;
                                printf("This amount is too much, you have successfully bought %.2f TRY.\n", (float)lame_money);
                            }
                        }
                        else if (b_cur=='E')
                        {
                            if (bal_btc >= money)
                            {
                                bal_eth += money*btc_eth;
                                bal_btc -= money;
                                printf("You have successfully bought %.2f ETH.\n", money*btc_eth);
                            }
                            else
                            {
                                lame_money = bal_btc * btc_eth;
                                bal_btc -= (lame_money * eth_btc);
                                bal_eth += lame_money;
                                printf("This amount is too much, you have successfully bought %.2f ETH.\n", (float)lame_money);
                            }
                        }
                        else printf("Error: Operation could not be completed.\n");
                        break;    
                        
                        
                    case 'E':
                        if (b_cur=='B')
                        {
                            if (bal_eth >= money)
                            {
                                bal_btc += money*eth_btc;
                                bal_eth -= money;
                                printf("You have successfully bought %.2f BTC.\n", money*eth_btc);
                            }
                            else
                            {
                                lame_money = bal_eth * eth_btc;
                                bal_eth -= (lame_money * btc_eth);
                                bal_btc += lame_money;
                                printf("This amount is too much, you have successfully bought %.2f BTC.\n", (float)lame_money);
                            }
                        }
                        else if (b_cur=='T')
                        {
                            if (bal_eth >= money)
                            {
                                bal_try += money*eth_try;
                                bal_eth -= money;
                                printf("You have successfully bought %.2f TRY.\n", money*eth_try);
                            }
                            else
                            {
                                lame_money = bal_eth * eth_try;
                                bal_eth -= (lame_money * try_eth);
                                bal_try += lame_money;
                                printf("This amount is too much, you have successfully bought %.2f TRY.\n", (float)lame_money);
                            }
                        }
                        else printf("Error: Operation could not be completed.\n");
                        break;
                    
                    default:
                        printf("Error: Operation could not be completed.\n");
                        break;
                }
                break;
                
            case 'S':
                scanf(" %f", &money);
                
                for (index=0 ; index<2 ; ++index)
                {
                    scanf(" %c", &cur);
                    scanf(" %f", &loss);
                    scanf(" %f", &exp_gain);
                    if (cur != 'E' && cur != 'B') error = 1;
                    loss *= 0.01;
                    exp_gain *= 0.01;
                    temp_gain = (((money-money*loss)*(1+exp_gain))*(1-loss))-money;
                    if (temp_gain > gain)
                    {
                        gain = temp_gain;
                        perm_cur = cur;
                        perm_loss = loss;
                        perm_cur = cur;
                        
                    }
                }
                if (error == 1) 
                {
                    printf("Error: Operation could not be completed.\n");
                    goto zum;
                }
                if (gain<0)
                {
                    printf("Trading currently is not logical.\n");
                    gain=-100.1;
                    goto label;
                }
                printf("%s is better with %.2f TRY gain. Buying it...\n", perm_cur=='E'?"ETH":"BTC", gain);
                
                bal_try -= money;
                
                if (perm_cur == 'E') bal_eth += money*try_eth;
                else bal_btc += money*try_btc;
                gain=-100.1;    
                label:
                error = 0;
                break;
            
            default:
                printf("Error: Operation could not be completed.\n");
                zum:
                break;
        }
    }
    return 0;
}