//room: tuyuan.c
inherit ROOM;

void create()
{
	set("short","��Է");
	set("long", @LONG
���Ǹ��������Է����ֻ����þ����ض����̲ݵ��ϳԲݡ�
���Ϸ�����԰�����洫���������޵ĺ��У�������һ����԰��
LONG );
	set("exits",([
		"east"  : __DIR__"sheyuan",
		"west"  : __DIR__"shoushe",
		"southwest" : __DIR__"zhuyuan",
	]));
	set("outdoors", "baituo");
	set("objects",([
		__DIR__"npc/baitu" : 2,
	]));
	setup();
}
