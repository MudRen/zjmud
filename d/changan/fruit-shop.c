//Room: fruit-shop.c

inherit ROOM;

void create ()
{
	set ("short", "ˮ����");
	set ("long", @LONG
������Ψһ��һ��ˮ���ꡣ�����������һ���ŵ���𣬿����и�
ʽ������ˮ���������ˮ��Ϊ�˱������ʣ�����ÿ��ӳ���Ĺ�԰�ÿ�
�������ġ�ˮ����Ů�ϰ���������������к��ſ��ˡ�
LONG);
	set("exits", ([
		"north"   : __DIR__"qixiang2",
	]));
	set("objects", ([
		__DIR__"npc/lanxiang"   : 1,
	]));

	setup();
}
