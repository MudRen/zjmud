inherit ROOM;

void create()
{
	set("short", "����");
	set("long",
	     "������ɽ�������ѵ����ڡ��Ա���һ�ප��������������Ů�ӵĿ�����\n"
	);
	set("exits", ([
		"west" : __DIR__"cedong",
		"south" : __DIR__"dongkou",
	]));
	set("objects",([
		__DIR__"npc/shanzei3" : 1,
	]));
	setup();
}
