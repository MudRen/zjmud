// Room: /d/xingxiu/yueerquan.c
inherit ROOM;
void create()
{
	set("short", "�¶�Ȫ");
	set("long", @LONG
�����������֮�⣬��ɳĮ�о�Ȼ��Ȫˮ��һ���峺��Ȫˮ�γ�һ��������
��״����������¶�Ȫ��������һƬ�ͱ�(cliff)�����ߴ������˵����졣
LONG );
	set("resource/water", 1);
	set("exits", ([
		"east" : __DIR__"shashan",
	]));
	set("item_desc", ([
		"���ͱڡ�" : "�ͱ����ƺ���һ����(hole)��\n"
		ZJOBACTS2"�궴:enter hole\n",
	]) );
	set("no_clean_up", 0);
	setup();
}

void init()
{
	add_action("do_enter", "enter");
}
int do_enter(string arg)
{
	object me;
	me = this_player();

	if( !arg || arg=="" ) return 0;
	if( arg=="hole" ) {
		if ( me->query_encumbrance() * 100 / me->query_max_encumbrance() < 20) {
			message("vision", me->name() + "һ����Ծ���˶��\n",
			environment(me), ({me}) );
			me->move("/d/xingxiu/mogaoku");
			message("vision", me->name() + "�Ӷ������˽�����\n",
			environment(me), ({me}) );
			return 1;
		}
		else {
		     write("�����ϱ��Ķ���̫�أ�������̫�ߣ��㹻���š�\n");
		     return 1;
		}
	}
}

