// nroad4.c

inherit ROOM;
void create()
{
	set("short", "��ѩɽɽ·");
	set("long", @LONG
��ѩɽ��´�ĵ��Ʋ������ߣ���Χ����һЩСɽ��������һ��
��Ժ��ɽ�������Ե��쳣�ߴ���Ժ��ƽ�����ͣ����ɴ�ʯ���ɣ�ǽ
���ʵ������խС��
LONG );
	set("exits", ([
		"north"   : __DIR__"nroad3",
		"westup"  : "/d/xueshan/shanmen",
		"east"  : "/d/xueshan/jingji/enter",
	]));
	set("outdoors", "xuedao");
	setup();
}

