#include <iostream>
#include <string>
using namespace std;

void cinCheck()
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(32767, '\n');
    }
}

enum TTT : char { X = 'X', O = 'O', EMTY = '�' };
struct TTT_field
{
    short int game_mode; // 0 - pvp, 1 - AI
    short int diff = 0;
    short int field_size = 0;
    TTT fieldsmall[3][3] = { {EMTY,EMTY,EMTY},{EMTY,EMTY,EMTY},{EMTY,EMTY,EMTY} };
    TTT fieldmedium[5][5] = { {EMTY,EMTY,EMTY,EMTY,EMTY},{EMTY,EMTY,EMTY,EMTY,EMTY},{EMTY,EMTY,EMTY,EMTY,EMTY}, {EMTY,EMTY,EMTY,EMTY,EMTY}, {EMTY,EMTY,EMTY,EMTY,EMTY} };
    string p1 = ""; //����� �������
    string p2 = "";
    char p1_ip[16] = "127.0.0.1"; //stub
    char p2_ip[16] = "127.0.0.1"; //stub
    TTT p1_f; //��� ������ ������ �����?
    TTT p2_f;
    int game_state = 0;
    string turn; //��� ���
    string winner;
};

//===================================================================================================
//������������� ����. ����� �������� ������. 
//===================================================================================================

void init(TTT_field &game_data)
{
    // TTT_field game_data - �������� ���� ������ ����. ��������� �� ��� ����� �� ������.
    cout << "����� ���������� � ���� '��������-������'!" << endl;
    string gm;

login:  //����� ����� ���� ������ ������� �����������
    game_data.game_mode = 2;
    //����� ����
    while (game_data.game_mode < 0 || game_data.game_mode > 1)
    {
        cout << "�������� ����� ����: PvP (����� ������ ������) ��� AI (������ ����������): ";
        cin >> gm;
        cinCheck();
        if (gm == "PvP" || gm == "pvp")
            game_data.game_mode = 0;
        else
            if (gm == "AI" || gm == "ai")
                game_data.game_mode = 1;
            else cerr << "������������ ����!" << endl;
    }
    cout << endl;

    //��������� ��
    if (game_data.game_mode == 1)
    {
        game_data.diff = 0;  //������ �� ��������������� ��� ����������� init
        while (game_data.diff < 1 || game_data.diff > 4)
        {
            cout << "�������� ���������. 1 - �������, 2 - �������, 3 - �������, 4 - Hurt Me Plenty: ";
            cin >> game_data.diff;
            cinCheck();
            cout << endl;
        }

        game_data.p1 = ""; //������ �� ������ ����������� init
        cout << "������� ��� ������: "; //��������� ������ ������ �� � ��������� ������������
        cin >> game_data.p1;
        cinCheck();
        game_data.p2 = "��";
        char temp1 = 0; //������ �� ������ ����������� init
        do
        {
            cout << "\n��� ������ �����(X/O)? ";
            cin >> temp1;
            cinCheck();
            if (temp1 == 'X' || temp1 == '�' || temp1 == 'x' || temp1 == '�')
            {
                game_data.p1_f = X;
                game_data.p2_f = O;
                break;
            }
            else if (temp1 == 'O' || temp1 == '�' || temp1 == 'o' || temp1 == '�')
            {
                game_data.p1_f = O;
                game_data.p2_f = X;
                break;
            }
            else
            {
                cerr << "�������� ������!" << endl;
                temp1 = 1;
            }
        } while (temp1 == 1); //����� ��������� ����� ������ ������ ��
    } //����� ��������� ��������� ��

//��������� ������� (pvp mode)
    else
    {
        char temp2 = 0;
        game_data.p1 = ""; //������ �� ������ ����������� init
        cout << "������� ��� ������� ������: ";
        cin >> game_data.p1;
        cinCheck();
    inputErr1:
        cout << "\n��� ������ ������ �����(X/O)? ";
        cin >> temp2; //�������� ��������� �� ������ ���������� �����
        cinCheck();
        switch (temp2)
        {
        case 'X':
        case 'x':
        case '�':
        case '�':
            game_data.p1_f = X;
            break;
        case 'O':
        case 'o':
        case '�':
        case '�':
            game_data.p1_f = O;
            break;
        default:
        {
            cerr << "�������� ������!" << endl;
            goto inputErr1;
        }
        }
        cout << endl;
        game_data.p2 = ""; //������ �� ������ ����������� init
        cout << "������� ��� ������� ������: ";
        cin >> game_data.p2;
        cinCheck();
        if (game_data.p1_f == X)
            game_data.p2_f = O;
        else game_data.p2_f = X;
    }//����� ����� ������ �� �������
    cout << endl;

    //============================================================================
    //��������� ������� �������� ����. ���� �� ��������� �����������, ����� ������
    //============================================================================
    if (game_data.game_mode == 1 && game_data.diff == 4)
        game_data.field_size = 5;
    else
    {
        for (;;)
        {
            cout << "�������� ������ �������� ���� (3, 5): ";
            cin >> game_data.field_size;
            cinCheck();
            if (game_data.field_size == 3 || game_data.field_size == 5)
                break;
            else
            {
                cout << "������������ ����!" << endl;
            }
        }
    }
    //==============================================================================

    //��������� �������������
    char y_n = 0;
    for (;;)
    {
        cout << "��������� (Y/N)? ";
        cin >> y_n;
        if (y_n == 'Y' || y_n == 'y' || y_n == '�' || y_n == '�')
        {
            cout << endl;
            break;

        }
        else if (y_n == 'N' || y_n == 'n' || y_n == '�' || y_n == '�')
        {
            cout << endl;
            goto login;
        }
    }
    return;
}

void fieldPrint(TTT_field& game_data)
{
    //����� ���� 3�3
    if (game_data.field_size == 3)
    {
        std::cout << "  " << "1 " << "2 " << "3 " << std::endl;
        for (int i1 = 0; i1 < 3; i1++)
        {
            std::cout << (i1 + 1) << " ";
            for (int i2 = 0; i2 < 3; i2++)
            {
                std::cout << game_data.fieldsmall[i1][i2] << " ";
            }
            std::cout << std::endl;
        }
    }
    else
        //����� ���� 5�5
    {
        for (int i1 = 0; i1 < 5; i1++)
        {
            for (int i2 = 0; i2 < 5; i2++)
            {
                std::cout << game_data.fieldmedium[i1][i2] << " ";
            }
            std::cout << std::endl;
        }
    }
}
//  ������������� ��������� ������, �� �� �����:
   //  ��������� �������������� 4 �������� ������. ������� ����������� �� 3:
   //  �) ��-��������� ������-����
   //  �) ����������� ���� 
   //  �) ��-��������� �������-����
   //  �) �� ����������� ������. 
   //  ������������ �� ����� ���������� �����/�������� �� ���� ����


//==================================================================================================
//�������� ���������� ������� ��������. ������� true - ������ ������ ��� ��� ��� ���������!
//==================================================================================================
int winCheck(TTT_field game_data) //0 - ���� ������������, 1 - ��������� ������, 2 - �����
{
    size_t draw_count = 0; //���� = 8 >> return 2;
    size_t countO, countX, count_0;

    for (size_t i = 0; i < game_data.field_size; i++) //�������� �� �������
    {
        countO = 0;
        countX = 0;
        count_0 = 0;
        for (size_t k = 0; k < game_data.field_size; k++) //������� �������� � ������
        {
            switch(game_data.fieldsmall[i][k])
            {
                case 'X':
                    countX++;
                    break;
                case 'O':
                    countO++;
                    break;
                case 'EMTY':
                    count_0++;
                    break;
            }
        }
        if (countX == 3 || countO == 3)
            return 1;
        else if (countX > 0 && countO > 0)
            draw_count++;
    }

    for (size_t k = 0; k < game_data.field_size; k++) //�������� �� ��������
    {
        countO = 0;
        countX = 0;
        count_0 = 0;
        for (size_t i = 0; i < game_data.field_size; i++) //������� �������� � �������
        {
            switch (game_data.fieldsmall[i][k])
            {
            case 'X':
                countX++;
                break;
            case 'O':
                countO++;
                break;
            case 'EMTY':
                count_0++;
                break;
            }
        }
        if (countX == 3 || countO == 3)
            return 1;
        else if (countX > 0 && countO > 0)
            draw_count++;
    }

    countO = 0; //�������� �� ��������� 1
    countX = 0;
    count_0 = 0;
    for (size_t i = 0; i < game_data.field_size; i++) 
    {
            switch (game_data.fieldsmall[i][i])
            {
            case 'X':
                countX++;
                break;
            case 'O':
                countO++;
                break;
            case 'EMTY':
                count_0++;
                break;
            }
    }
    if (countX == 3 || countO == 3)
        return 1;
    else if (countX > 0 && countO > 0)
        draw_count++;

    countO = 0; //�������� �� ��������� 2
    countX = 0;
    count_0 = 0;
    for (size_t i = 0; i < game_data.field_size; i++)
    {
        switch (game_data.fieldsmall[i][(game_data.field_size - 1) - i]) //������� �������� �� ��������� �� ������� �������� ����
        {
        case 'X':
            countX++;
            break;
        case 'O':
            countO++;
            break;
        case 'EMTY':
            count_0++;
            break;
        }
    }
    if (countX == 3 || countO == 3)
        return 1;
    else if (countX > 0 && countO > 0)
        draw_count++;

    //�������� �� �����, ����� �� �������
    if (draw_count == 8)
        return 2; //�����
    else
        return 0;
}
