// Room: /d/fuzhou/fzroad4.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
	set("short", "���ӹŵ�");
	set("long", @LONG
����������������ɽ�������������Ĺ���̣����ղ�����⡣
ɽ�ж������޳�û�޳�����·������
LONG );
	set("exits", ([
		"southwest" : __DIR__"fzroad5",
		"northeast" : __DIR__"yanping",
	]));
	set("objects", ([
		"/clone/beast/wubushe" : 1,
	]));
	set("outdoors", "fuzhou");

	set("resource/snake", ({ "/clone/beast/dushe",
				 "/clone/beast/fushe",
				 "/clone/beast/wubushe", }));

	setup();
}
