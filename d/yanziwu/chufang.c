//chufang.c
inherit ROOM;
void create()
{
	set("short","����");
	set("long",@LONG
���Ǽ���ĳ�������ʦ����չʾ���Ե���⿾��������������
�����˴������εĲ��㡣
LONG );
	set("exits",([
	    "north" : __DIR__"xiaoting",
	]));
	set("objects",([
	     __DIR__"npc/nanpu" : 1,
	]));
	set("resource/water", 1);
	setup();
}
