//      houmen.c ����
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
����ѩɽ�µĺ��š�һƬ���������ģ������������
��Ҳ�㣬����Ҳ�����Ǻ��ţ���Ȼδ�⺮�ᣬ��Ҳ�ܿ�
��Ҵ�š�
LONG );
	set("exits", ([
	    "south" : __DIR__"houyuan",
	]));
	setup();
}

