// Room: /d/guanwai/chufang.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�������ƣ��������ڣ���ζ�˱Ƕ�������ǽ��һ����̨��֧��һ
�ڴ����������������������࣬�Աߵ�һ���������Ű�����ͷ��һ
�������˾۾�����������ų���������ʲ��
LONG );
	set("exits", ([
		"east" : __DIR__"shizilu",
	]));

	set("objects",([
		__DIR__"obj/wan" : 2,
		__DIR__"obj/mantou" : 5,
	]));

	set("resource/water", 1);
	setup();
}
