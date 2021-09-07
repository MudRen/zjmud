// road3.c
inherit ROOM;

void create()
{
	set("short", "����·");
	set("channel_id", "��������");
	set("long", @LONG
������һ������·�ϡ�������ȥ���������Կ���ƽ���ݡ���
���������ǿ쵽�ˡ�
LONG );
	set("outdoors", "heimuya");
	set("exits", ([
		"north" : "/d/tulong/yitian/road3",
		"east" : "/d/beijing/ximenwai",
		"west" : __DIR__"pingdingzhou",
	]));

	setup();
}

int start_yitian()
{
	shout(HIR "\n������������" NOR+WHT "������߼�����¶����м������" NOR );
	shout(HIR "\n������������" NOR+WHT "�������������콣���������У��б��¾;��ܵ����������á�"NOR"\n" );
	CHANNEL_D->do_channel(this_object(), "chat", "����һ��Я�����콣���������£����콣����������");
	set("open",1);
	call_out("clear_yitian",1800);
	return 1;
}

int clear_yitian()
{
	mixed *files;
	string file;
	object *inv,room;
	int i,j;

	files = list_dirs("/d/tulong/yitian/");
	for(i=0;i<sizeof(files);i++)
	{
		file = "/d/tulong/yitian/"+files[i];
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
							tell_object(inv[j],"�㱻ǿ���뿪�����£�\n");
							inv[j]->move("/d/heimuya/road3");
						}
					}
				}
			}
		}
	}
	this_object()->delete("open");
	CHANNEL_D->do_channel(this_object(), "chat", "���콣�����ѽ�����");
	return 1;
}

int valid_leave(object me, string dir)
{
	if (dir=="north"&&!this_object()->query("open"))
		return notify_fail("�����ѹرգ�����ʱ��ÿ������9:30-10:00��\n");
      if (dir=="north"&& me->query("combat_exp", 1)<1000000 )
		return notify_fail("����ô���΢���书�����޷������������������콣�ɣ�\n");
	//if (dir=="north"&&!wizardp(me))
	//	return notify_fail("�����У���ʱ���ܽ��롣\n");
	return 1;
}
