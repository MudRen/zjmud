//houyuan.c

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "��Ժ");
        set("long", @LONG
��������ƺ���һ����Ժ�ˣ����ܶ���������ƺ��ܾ�û��������ԶԶ
��ȥ�ǹ�����ů��Ĵ��ڡ�ֻ������ǽ���ƺ���Щ��֡�����ǽ�ܸо�������
��һ��������ǽȷ������һС�����䣬�ƺ����ԴӶ������ȥ��
LONG
    );
	set("no_fight",1);
	set("action_list", ([
		"����":"tiao chuang",
		"�궴":"zuan dong",
	]));
	setup();
}
void init()
{
	add_action("do_jump", ({"jump", "tiao"}));
	add_action("do_enter", ({"zuan"}));
}
int do_jump(string arg)
{
	object room,me = this_player();
    if( arg == "chuang" || arg == "window" || arg == "chuanghu" || arg == "chuangkou")
    {
		if(me->query_skill("dodge")<100) 
		{
			message_vision(HIY"\n$N����һ��������Ӵ�������ȥ��"NOR"\n",me);
			return notify_fail("����ɽ��ǰ����һ�죺��λ"+RANK_D->query_respect(me) +"����Ҫ��ʲô����"NOR"");
		}
		if (!(room = find_object(__DIR__"woshi")))
			room = load_object(__DIR__"woshi");
		if(!room)
		{ 
			tell_object(me,HIR"\n��������ô�������ֶ�����ԭ��!\n");
			log_file("quest/LCHJ", sprintf("%s(%s)ȱ��woshi.c�ļ���\n", me->name(1),me->query("id")) );	
		}
		else
		{
			message_vision(HIY"\n$N����һ������������ɽ��ע�⣬ͻȻֱ�ӴӴ������˽�ȥ��"NOR"\n", me);
			me->move(room);
			me->start_busy(1);
			tell_room(environment(me),"\nֻ��һ����Ӱ���������ԭ����"+me->name()+"�Ӵ��������˽�����"NOR"\n", ({me}));                       	
		}
		return 1;
	}
	return 0;
}
int do_enter(string arg)
{
	object room,me = this_player();
    if( arg == "dong" )
    {
		if (!(room = find_object(__DIR__"citang")))
			room = load_object(__DIR__"citang");
		if(!room)
		{ 
			tell_object(me,HIR"\n��������ô�꣬���ֶ�����ԭ��!\n");
			log_file("quest/LCHJ", sprintf("%s(%s)ȱ��citang.c�ļ���\n", me->name(1),me->query("id")) );	
		}
		else
		{
			message_vision(HIY"\n$N����̽���������Ӷ������˽�ȥ��"NOR"\n", me);
			me->move(room);
			me->start_busy(1);
			tell_room(environment(me),"\nֻ��һ���˴�һ���������˳�����ԭ����"+me->name()+"��"NOR"\n", ({me}));                       	
		}
		return 1;
	}
	return 0;
}

