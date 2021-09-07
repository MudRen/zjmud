#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "����֮��");
	set("long", @LONG
������Ǵ�֮�����˻��Ĵ��Ž�ʯ����������������������һȺȺ��
Ÿ��ŷŷ..���ؽ��ţ���ʱ�����Ծ�����棬��������˻����������Ҵ�
��(chuan)�� �������ż����������ˣ��˴��ɶɹ��󺣵��ﺣ����һ�ˡ�
����һֱ�߾����ྩ�ˣ�������һ���޼ʵĴ󺣡���Ŀ���������������ؿ�
���������⳩����ȷ��һ���þӴ���
LONG );
	set("exits", ([
		"west" : __DIR__"road10",
		"north" : "/d/tulong/tulong/haian",
	]));
	set("item_desc", ([
		"���󴬡�" : "һ�Ҵ󷫴�����úܽ�ʵ���������Գ�Զ���ġ�\n",
	]));
	set("objects", ([
		"/d/shenlong/npc/chuanfu" :1,
	]));
	set("action_list", ([
		"�ϴ�" :"shangchuan",
	]));
	set("max_room", 3);
	set("outdoors", "beijing");
	setup();
}

void init()
{
	add_action("moveto","shangchuan");
}

int moveto()
{
	object me = this_player();

      if (me->query("combat_exp", 1)<1000000 )
		return notify_fail("����ô���΢���书�����޷��������������������ɣ�\n");
	if (!this_object()->query("open"))
		return notify_fail("�����˳���ʱ��(20:30-20:35)��ֻ�õ���һ���ˡ�\n");
	me->move("/d/tulong/tulong/boat");
	tell_object(me,"�������ڴ˵Ⱥ�Ƭ�̣��Ժ������\n");
	return 1;
}

int start_tulong()
{
	object boat;

	shout(HIR "\n������������" NOR+WHT "�׹�������һ����Ц��" NOR );
	shout(HIR "\n������������" NOR+WHT "�׹��٣�����ӥ�̵õ���������������������ɽ�������ﵶ������ᡣ"NOR"\n" );
	set("open",1);
	if(!(boat=find_object("/d/tulong/tulong/boat")))
		boat=load_object("/d/tulong/tulong/boat");
	call_out("arrive1",300,boat);
	call_out("clear_tulong",1800);
	return 1;
}

int clear_tulong()
{
	mixed *files;
	string file;
	object *inv,room;
	int i,j;

	files = list_dirs("/d/tulong/tulong/");
	for(i=0;i<sizeof(files);i++)
	{
		file = "/d/tulong/tulong/"+files[i];
		if(file_size(file))
		{
			room = find_object(file);
			if(room)
			{
				inv = all_inventory(room);
				if(sizeof(inv))
				{
					for(j=0;j<sizeof(inv);j++)
					{
						if(playerp(inv[j]))
						{
							tell_object(inv[j],"�㱻ǿ���뿪���ﵶ�����᳡��\n");
							inv[j]->move("/d/beijing/haigang");
						}
					}
				}
			}
		}
	}
	CHANNEL_D->do_channel(this_object(), "chat", "�����������ѽ�����");
	return 1;
}

int arrive1(object boat)
{
	tell_room(boat,HIC "\n��ӥ�̵Ĵ��ϣ�ֻ���������ֺ������������ˣ����������������ʻ����"NOR"\n");
	tell_room(boat,HIB "\n���ڴ���������Ư��......�㲻���е�˯�����ʡ�"NOR"\n");
	this_object()->delete("open");
	call_out("arrive2",300,boat);
	return 1;
}

int arrive2(object boat)
{
	object *inv;
	int i;

	tell_room(boat,"\n��ͻȻ����һ�����ȣ������ˣ��´��ɡ�����ʱ�����񣬸�����ӥ�̽������˴���"NOR"\n");
	inv = all_inventory(boat);
	inv->move("/d/tulong/tulong/daobian");
	inv->set_temp("bishi",1);
	return 1;
}

int valid_leave(object me, string dir)
{
	if (dir == "north" && ! playerp(me))
		return 0;

	return ::valid_leave(me, dir);
}
