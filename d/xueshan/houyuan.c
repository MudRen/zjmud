//      houyuan.c ��Ժ
inherit ROOM;

void create()
{
	set("short", "��Ժ");
	set("long", @LONG
������ѩɽ�µĺ�Ժ����Ժ�������˼������ѩ�ɣ�
�ڰ׻λε�ѩɽ�����£�����ƮȻ�������Ķ����ϱ�����
�䳡�������Ǻ��š�
LONG );
	set("outdoors", "xueshan");
	set("exits", ([
		"eastdown" : __DIR__"dilao",
		"north" : __DIR__"houmen",
		"south" : __DIR__"chang3",
	]));
	setup();
}

