// gytoad2.c ��԰С·
// by Java

inherit ROOM;
#include <ansi.h>
int do_zhai(string arg);
void create()
{
	set("short", "��԰");
	set("long", @LONG
�����ɵ��߽���԰��԰����Ӣ�ͷף������������֣�ʢ���ŷۺ���һ���
����һƬ���������ߡ��м�ȴ��һ��ڸ���Ķ�Ĵ���(tree)����ס����ô�һ
Ƭ����
LONG );
	set("outdoors", "wudang");
	set("item_desc", ([
		"tree" : 
"����һ���˲ι�������������˲ι�����˵ժ�³��˶��书������кô���\n"
	]));
	set("exits", ([
		"west" : __DIR__"gyroad1",
	]));
	set("guocount",1);
	setup();
}

void init()
{
	add_action("do_zhai","zhai");
}

int do_zhai(string arg)
{
	object guo;
	if (! arg || arg == "")
	{
		message_vision("����ժʲô��\n", this_player());
		return 1;
	}
	if (arg == "guo" || arg == "renshen guo")
	{
		if (uptime() < 1800)
		{
			message_vision("�˲ι�δ���أ�$N��һ�������ɡ�\n",
				       this_player());
			return 1;
		}
		if (query("guocount") > 0 && random(2)==1)
		{
			message_vision("$N���˲ι�����ժ��һ����͸��" HIR
				       "�˲ι���"NOR"\n", this_player());
			guo = new(__DIR__"obj/renshenguo");
			guo->move(this_player());
			add("guocount", -1);
			return 1;
		} else
		{
			set("guocount",0);
			message_vision("$N���Ǻÿ��������˲ι��ձ�ժ�ߡ�\n",
				       this_player());
			return 1;	     
		}
	}
	return 0;
}

