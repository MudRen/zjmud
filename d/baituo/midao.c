//midao.c

inherit ROOM;

void create()
{
	set("short","�ܵ�");
	set("long","��������ڵ��ܵ����������ɽ����Ϊ��ֱ����ԭ������ġ�\n"); 
	set("exits" , ([
		"east" : "/d/city/beidajie1",
	]));
	set("objects",([
		__DIR__"obj/shenshe" : 1,
	]));
	setup();
}
