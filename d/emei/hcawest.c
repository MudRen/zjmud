//Room: hcawest.c �����ֲ��

inherit ROOM;
string look_chuang();
string look_paizi();

void create()
{
      set("short","�����ֲ��");
      set("long",@LONG
�����ǽ𶥻����������ǽӴ���ͼ������ĵط������ڰ��ż������ӣ�
����Χ���������ӡ�ǽ�����ż����ֻ���ǽ��һ����ܣ����ϰ������顣�м�
λ���������Ʒ����������ǽ�ϵ��ֻ����ļ��ϵľ��顣����������ʮ��
��Ĺ�������һλʦ̫�����йس��ҵ��¡�һ��ʮ�����Сʦ̫����æǰæ��
�д����ˡ��ϱ����ȴ��ӡ�
LONG);
      set("objects", ([
	   CLASS_D("emei") + "/wenqing" : 1,
      ]));
      set("item_desc", ([
	  "��������" : (: look_chuang :),
	  "�����ӡ�"  : (: look_paizi :),
      ]));
      set("exits",([ /* sizeof() == 1 */
	  "east"   : __DIR__"hcazhengdian", 
      ]));
      setup();
}

string look_chuang()
{
    return "������Կ�����üɽ������ɽ���������и�С���ӡ�\n";
}
string look_paizi()
{
    return "������д�ţ���������Ϊ���أ�����"ZJURL("cmds:jump chuang")+ZJSIZE(15)"��(jump)"NOR"����\n";
}
void init()
{
	add_action("do_jump", "jump");
}
int do_jump(string arg)
{
	object me;
	if (!arg ||arg !="chuang") return 1;
	me = this_player();
	message_vision("$N���˲�ע�⣬�������⡣\n",me);
	me->move(__DIR__"xiaoshulin1");
	message_vision("$N�ӻ�����������������\n",me);
	return 1;
}
