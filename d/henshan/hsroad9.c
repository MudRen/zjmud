// Room: /d/henshan/hsroad9.c ����ɽ��
// Modified by Java on Feb.14.1998
inherit ROOM;

void create()
{
	set("short", "����ɽ��");
	set("long", @LONG
�����������һ��ɽ�ڡ����������ϵĴ����ɽ�������Ǻ��ϵ�
�ؽ硣���Ϲ㶫������ʢ�����к���֮ʿ��
LONG );
	set("outdoors", "hengyang");

	set("exits", ([
		"northdown" : __DIR__"hsroad5",
		"southdown" : "/d/foshan/nanling",
	]));
	setup();
}

