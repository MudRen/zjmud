//Room: xiaojiuguan.c

inherit ROOM;

void create ()
{
	set ("short", "С�ƹ�");
	set ("long", @LONG
����һ��С�ƹݣ����Ӳ����Ǻܿ�����ˮҲ�ǳ���������������
�ģ�����ȴ��Ȼ�����������ˣ�Ҳ��֪�����������ȾƵģ���������
����λ���ڹ�̨������ϰ��
LONG);
	set("exits", 
	([ //sizeof() == 1
		"north" : __DIR__"liande-nankou",
	]));
	set("objects", 
	([ //sizeof() == 1
		__DIR__"npc/ruhua" : 1,
	]));

	set("no_clean_up", 0);
	setup();
}
