//ROM dating

inherit ROOM;

void create()
{
	set("short", "����");
	set("long",
	     "���ǡ�����ɽׯ���Ĵ������ڲ����輫������������һ�ź�ɫ̴ľ\n"
	 "����������·��ž����Ļ�ƿ��һЩ���Ĵ������ıڹ������ҵ��ֻ���\n"
	);

	set("exits", ([
		"north" : __DIR__"liangong",
		"southdown" : __DIR__"yuanzi",
	]));
 
	set("objects",([
		CLASS_D("ouyang") + "/ouyangfeng" : 1,
		__DIR__"npc/yahuan" : 2,
	]));
	set("no_beg", 1);

	setup();

}
