//test.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", HIY"�ʷ�"NOR);
	set("long", @LONG
��������ݵ��ʷ����ı�ѩ�׵�ǽ���м��и����̨����̨ǰ�Ϸ�����һ
�����ӣ�paizi���� ���Ｗ��������ȡǮ�����ݵ��ӣ��Ե�ʮ�����ӡ��ʷ�
�����Ǹ���ʮ�������ͷ�����������˽�������Ц������ӭ��������
LONG
	);

	set("exits", ([
		"north" : __DIR__"zoulang6",
	]));
	set("no_fight",1);
	set("objects", ([
	]));

	setup();
}
