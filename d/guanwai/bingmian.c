// /guanwai/bingmian.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�������ɻ����Ľ��棬���Ѷ����˼��ߺ�ļ�������˻���ƥ��������
�ɺ��⽭�������Σ�ա����������к��Ļ�ѩ������������һƬ��ֻ����
�侭������֮����¶��һ����ɫ�ı�·��
LONG );
	set("exits", ([
		"east"  : __DIR__"damenkan",
		"west"  : __DIR__"chuanchang",
	]));
	set("outdoors", "guanwai");
	setup();
}

int valid_leave(object me, string dir)
{
	object obj;
	int i;

	switch (NATURE_D->query_month())
	{
	case 11: case 12: case 1: case 2: case 3: case 4:
		message_vision("$N���ڱ����ϸ�·������֨��֨�µ��졣\n\n", me);
		if (random(me->query_dex()) + me->query_dex() / 2 < 20)
		{
			me->receive_wound("qi", 20);
			me->receive_damage("qi", 10);
			message_vision("$Nֻ���ý���һ����ȫ���ڿն��𣬽��ʵʵ��ˤ���˱����ϣ�\n", me);
		}
		break;
	default:
		me->set_temp("die_reason", "��Ϊ���濪��������������������");
		me->die();
		write("�Ժ��Ҫע������\n");
		return -1;
	}
	return 1;
}
