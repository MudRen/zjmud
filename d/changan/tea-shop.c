//Room: tea-shop.c

inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
���跿�ǳ����������Ӿ۵ĳ���������������˵İٷ���һЩľ
�Ƶ����Ρ�һ��˵��������������ϲ����Ľ���ʲô��һЩ���һ��Ʒ
�裬һ�����飬һ�߻�����ɫ��ͷ�Ӷ��������Ҫ����������ƹʺ�ҥ
�ԣ�������׼û��
LONG);
	set("exits", ([ /* sizeof() == 1 */
		"south" : __DIR__"qixiang2",
	]));
	set("objects", ([
		__DIR__"npc/teawaiter" : 1,
		__DIR__"npc/laoren" :1,
	]) );

	setup();
}
