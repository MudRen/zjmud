//citang.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
������԰�������������ڡ�����յ����ģ��������ǻҳ������ζ�����
Ϊ���ƣ������ܳ�ʱ��û�˹���ˡ��ݽ�������һ�������ǻң���ͷ�������
���򸾣�һ���������������
LONG
        );
        	 
        set("exits", ([
               "southwest" : __DIR__"houhuayuan",               
        ]));
	set("no_fight",1);
        set("objects", ([
        ]));
	set("action_list", ([
		"�궴":"zuan dong",
	]));
        setup();
}
void init()
{
	add_action("do_enter", ({"zuan"}));
}
int do_enter(string arg)
{
	object room,me = this_player();
    if( arg == "dong" )
    {
		if (!(room = find_object(__DIR__"houyuan2")))
			room = load_object(__DIR__"houyuan2");
		if(!room)
		{ 
			tell_object(me,HIR"\n��������ô�꣬���ֶ�����ԭ��!\n");
			log_file("quest/LCHJ", sprintf("%s(%s)ȱ��houyuan2.c�ļ���\n", me->name(1),me->query("id")) );	
		}
		else
		{
                        message_vision(HIY"\n$Nή��һ���������Ȼ�ҵ�һ���ں����Ķ��ڡ�\n$N����̽���������Ӷ������˽�ȥ��"NOR"\n", me);
			me->move(room);
			me->start_busy(1);
                        tell_room(environment(me),HIC"\nֻ��һ���˴�һ���������˳�����ԭ����"+me->name()+"��"NOR"\n", ({me}));                              
		}
		return 1;
	}
	return 0;
}
