//Room: /d/dali/hongsheng2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","��ʥ����");
	set("long",@LONG
�����Ǻ�ʥ�����ڲ�������ǽ���϶����з��裬�����÷���
̧ͷ���������Կ�������������«����ɡ�ǡ����ּ��������еȡ�
ɡ�ǳɰ˽��Σ����Ϲ��з��졣
LONG);
	set("exits",([ /* sizeof() == 1 */
	    "down"   : __DIR__"hongsheng1",
	    "up"     : __DIR__"hongsheng3",
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	int c_skill;

	me = this_player();

	if (dir == "up" )
	{
		c_skill = (int)me->query_skill("dodge", 1);
		if (me->query("qi") > 40)
		{
			me->receive_damage("qi", 20 + random(20));
			if (me->can_improve_skill("dodge") && c_skill < 100)
				me->improve_skill("dodge", 1 + c_skill / 15);
			tell_object(me,"������һ��¥����Щ���ˡ�\n");
		} else
		{
			me->set("qi", 0);
			tell_object(me,"��ʵ�����������ˡ�\n");
			return -1;
		}
	}
	return 1;
}
