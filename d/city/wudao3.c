// Room: /city/wudao3.c

#include <ansi.h>

inherit __DIR__"underlt";

void create()
{
	set("short", "�����");
	set("long", @LONG
���������滷ɽ��ֻ�б����������ڵ�һƺɽ��ƽ�ء�ɽ��ɽ�������λ�
�����죬ɽ���µ�ƽ���̲������м�����˸���̨������һ���ȥ�������
�������α����ȫ��
LONG );
	set("outdoors", "city");
	set("exits", ([
		"leitai"      : __DIR__"leitai",
		"northeast"   : __DIR__"wudao1",
		"northwest"   : __DIR__"wudao2",
	]));
	set("no_fight", 1);
	setup();
	init_here();
	replace_program(__DIR__"underlt");
}
