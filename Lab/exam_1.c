#include <stdio.h>

int main()
{
    int running=1, money=0, loan=0, total_loan=0, payed_depth=0, total_tax=0;
    int index=0;
    int peasent=0, burgher=0, nobility=0;
    int army_count=0;
    int monthly_balance=0, total_op_cost=0;
    int forgive_time=0;
    float init_cost, op_cost, army_pow;
    double score, selected_score=0.0;
    float selected_init, selected_op;
    char opcode, army_char, selected_army;
    
    while (running)
    {
        scanf(" %c", &opcode);
        
        switch (opcode)
        {
            case 'K':
                scanf("%d", &money);
                break;
                
            case 'Q':
                printf("Our reign may never end...\n");
                running = 0;
                break;
            
            case 'R':
                printf("We have %d ducats in our treasury.\n", money);
                break;
            
            case 'L':
                scanf("%d", &loan);
                total_loan += loan;
                money += loan;
                break;
                
            case 'P':
                scanf("%d", &payed_depth);
                money -= payed_depth;
                total_loan -= payed_depth;
                if (total_loan <= 0)
                {
                    total_loan = 0;
                    printf("We have no remaining debts.\n");
                }
                break;
            
            case 'F':
                if (total_loan > 1)
                    printf("We have %d ducats of remaining loans.\n", total_loan);
                else
                    printf("We have %d ducat of remaining loans.\n", total_loan);
                break;
            
            case 'T':
                scanf("%d", &peasent);
                scanf("%d", &burgher);
                scanf("%d", &nobility);
                total_tax = (peasent*2) + (burgher*5) + (nobility*10);
                if (total_tax > 1)
                    printf("Our kingdom has %d ducats income.\n", total_tax);
                else
                    printf("Our kingdom has %d ducat income.\n", total_tax);
                break;
            
            case 'A':
                for (index=0 ; index<3 ; ++index)
                {
                    scanf(" %c", &army_char);
                    scanf("%f", &init_cost);
                    scanf("%f", &op_cost);
                    scanf("%f", &army_pow);
                    score = (army_pow / (init_cost + (12*op_cost)));
                    if (score > selected_score)
                    {
                        selected_score = score;
                        selected_army = army_char;
                        selected_init = init_cost;
                        selected_op = op_cost;
                    }
                }
                printf("Our army will be %c, since its good score of %.4f.\n", selected_army, selected_score);
                init_cost = 0;
                op_cost = 0;
                army_pow = 0;
                selected_score = 0;
                break;
            
            case 'C':
                if ((money-selected_init) >= 0)
                {
                    money -= selected_init;
                    army_count = army_count + 1;
                    total_op_cost += selected_op;
                    if (army_count == 1)
                        printf("Our army is stronger now. We have %d army serving our kingdom.\n", army_count);
                    else if (army_count > 1)
                        printf("Our army is stronger now. We have %d armies serving our kingdom.\n", army_count);
                }
                else
                {
                    printf("We can not afford this army for now.\n");
                }
                break;
                
            case 'M':
                monthly_balance = total_tax - total_op_cost;
                money = money + monthly_balance;

                printf("This month our kingdom's balance is %d.\n", monthly_balance);
                
                if (money < 0)
                {
                    forgive_time += 1;
                    if (forgive_time >= 2)
                    {
                        army_count = 0;
                        total_loan = 0;
                    }
                }
                break;
                
            default:
                break;

        }
    }
    
    return 0;
}
