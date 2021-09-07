// Room: /lingzhou/luorilin2.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
	set("short", "������");
	set("long", @LONG
������һƬ��Բ�����ɭ�֣����й�ľ���죬������գ�����������
�����ֵķ�ľ�����������������ľ������������ϣ����˺ͱ���
�����ȱȽ��ǣ�һ���������·����ͨ��ǰ����
LONG );
	set("exits", ([
		"north"     : __DIR__"tulu",
		"southwest" : __DIR__"dalu",
	]));
	set("objects", ([
		"/d/city/obj/shuzhi" : 1,
		"/clone/beast/dushe" : 1,
	]));

	set("resource/snake", ({ "/clone/beast/jinshe",
				 "/clone/beast/dushe",
				 "/clone/beast/fushe",
				 "/clone/beast/wubushe",
				 "/clone/beast/qingshe", }));

	set("outdoors", "lingzhou");
	setup();
}
