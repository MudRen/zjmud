//Room: baoxiangsi.c

inherit ROOM;

void create ()
{
	set ("short", "������");
	set ("long", @LONG
�����¹�ģ��󣬷����ǧ����Ժ�������������������ﾡ�Ǹ߸�
ʯ�ڣ���������Ʋ�һ�ᣬ��Ȼ�ֲ�����ʱ�ĵ�·��������һ�����
ʯ���ƺ���������������ٺٶ�Ц��
LONG);
	set("exits", 
	([ //sizeof() == 2
		"north" : __DIR__"qinglong1",
		"south" : __DIR__"baodian",
	]));
	set("objects", 
	([ //sizeof() == 2
		__DIR__"npc/monk" : 2,
	]));

	setup();
}
