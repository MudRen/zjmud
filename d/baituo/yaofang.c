//room: /d/btshan/restroom.c
inherit ROOM;

void create()
{
	set("short","ҩ��");
	set("long", @LONG
�����Ǽ�ҩ������ǽ����һֻ��ҩ���������������ӣ��ϱ߰���
����ҩ�õ�ƿƿ�޹ޡ�����һ��ҩƿ(bottle)��ֻװ����ˮ����ҩʦ��
λС����������﷢������֪����ʲô�����������ɵĳ��ȡ�
LONG
	);

	set("exits",([
		"north" : __DIR__"changlang",
	]));

	set("item_desc",([
		"bottle" : "ҩ�������ű�ǩ�����ߵ��ࡻ������"
			   "��Ʒ������������Ч����ѡ�\n",
	]));

	set("objects",([
		__DIR__"npc/xiaoqing" : 1,
	]));

	setup();
}
