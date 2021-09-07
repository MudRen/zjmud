// afkd.c

#define AFK_DIR "/adm/afk/"

inherit F_DBASE;
inherit F_SAVE;

void load_afks();
void print();

void create()
{
	seteuid(ROOT_UID);
	if( !restore() && !mapp(dbase) )
		load_afks();
}

string query_save_file() { return DATA_DIR + "afkd"; }

string *afk_list()
{
	return keys(dbase);
}

void load_afks()
{
	string str, str2, *files, *tmp, *tmp2, file;
	int i, j, num;
	mapping bonusd;
	mapping bonuso;
	mapping need,npc,room;

	dbase = ([]);
	files = get_dir(AFK_DIR);
	for(i=0;i<sizeof(files);i++)
	{
		file = read_file(AFK_DIR+files[i]);
		if (!file) continue;
		bonusd = ([]);
		bonuso = ([]);
		need = ([]);
		npc = ([]);
		room = ([]);
		tmp2 = ({});
		tmp = explode(file, "\n");
	   	for (j=0;j<sizeof(tmp);j++)
		{
			if(tmp[j] == "" || tmp[j][0] == '\n' || strsrch(tmp[j],"//")==0)
			{
				continue;
			}
			else if(sscanf(tmp[j],"#%s",str) == 1)
			{
				if(sscanf(str,"NAME %s",str) == 1)
				{
					set(files[i]+"/name",str);
				}
				else if(sscanf(str,"ROUND %d",num) == 1)
				{
					set(files[i]+"/round",num);
				}
				else if(sscanf(str,"TYPE %d",num) == 1)
				{
					set(files[i]+"/type",num);
				}
				else if(sscanf(str,"ROOM %s",str) == 1)
				{
					if(sscanf(str,"%s:%d",str2,num) == 2)
					{
						room[str2] = num;
					}
					else if(sscanf(str,"%s:%s",str,str2) == 2)
					{
						room[str] = str2;
					}
				}
				else if(sscanf(str,"NEED %s",str) == 1)
				{
					if(sscanf(str,"%s:%d",str,num) == 2)
					{
						need[str] = num;
					}
				}
				else if(sscanf(str,"NPC %s",str) == 1)
				{
					if(sscanf(str,"%s:%s",str,str2) == 2)
					{
						npc[str] = str2;
					}
				}
				else if(sscanf(str,"DATA %s",str) == 1)
				{
					if(sscanf(str,"%s:%d",str,num) == 2)
					{
						bonusd[str] = num;
					}
				}
				else if(sscanf(str,"OBJ %s",str) == 1)
				{
					if(sscanf(str,"%s:%d",str,num) == 2)
					{
						bonuso[str] = num;
					}
				}
			}
			else tmp2 += ({ tmp[j] });
		}
		set(files[i]+"/msg",tmp2);
		set(files[i]+"/bonusd",bonusd);
		set(files[i]+"/bonuso",bonuso);
		set(files[i]+"/room",room);
		set(files[i]+"/need",need);
		set(files[i]+"/npc",npc);
	}
	save();
}

void check_user(object me)
{
	string str,file,*msg,*ds,*os,*rs,*needs,*npcs;
	int i,type,round,step;
	object obj,room,env;
	mapping d,o,r,need,npc;

	if(me->query("afk"))
	{
		env = environment(me);
		file = me->query("afk/file");
		room = me->query("afk/room");
		if(!mapp(query(file))||env!=room)
		{
			me->delete("afk");
			return;
		}

		need = query(file+"/need");
		if(sizeof(needs=keys(need)))
		{
			for(i=0;i<sizeof(needs);i++)
			{
				if(me->query(needs[i])<need[needs[i]])
				{
					tell_object(me,"你的"+to_chinese(needs[i])+"需要达到"+need[needs[i]]+"才能进行挂机"+query(file+"/name")+"。\n");
					me->delete("afk");
					return;
				}
			}
		}

		r = query(file+"/room");
		if(sizeof(rs=keys(r)))
		{
			for(i=0;i<sizeof(rs);i++)
			{
				if(env->query(rs[i])!=r[rs[i]])
				{
					tell_object(me,"你所在的地方不能进行挂机"+query(file+"/name")+"。\n");
					me->delete("afk");
					return;
				}
			}
		}

		npc = query(file+"/npc");
		if(sizeof(npcs=keys(npc)))
		{
			for(i=0;i<sizeof(npcs);i++)
			{
				if(!objectp(present(npc[npcs[i]],env)))
				{
					tell_object(me,"你需要有"+npcs[i]+"在身边才能进行挂机"+query(file+"/name")+"。\n");
					me->delete("afk");
					return;
				}
			}
		}

		step = me->query("afk/step");
		type = query(file+"/type");
		round = query(file+"/round");
		msg = query(file+"/msg");

		if(type == 1)
		{
			if(step < round)
				tell_object(me,msg[random(sizeof(msg))]+"\n");
		}
		else
		{
			round = sizeof(msg);
			if(step < round)
				tell_object(me,msg[step]+"\n");
		}

		step++;
		if(step > round)
		{
			d = query(file+"/bonusd");
			o = query(file+"/bonuso");
			if(sizeof(ds=keys(d)))
			{
				str = "你的";
				for(i=0;i<sizeof(ds);i++)
				{
					if(file_size(SKILL_D(ds[i])+".c")>0)
					{
						me->improve_skill(ds[i],d[ds[i]]);
						str += sprintf("%s熟练 + %d",to_chinese(ds[i]),d[ds[i]]);
					}
					else
					{
						me->add(ds[i],d[ds[i]]);
						str += sprintf("%s + %d",to_chinese(ds[i]),d[ds[i]]);
					}
					if(i<(sizeof(ds)-1)) str += "，";
					else str += "。\n";
				}
				tell_object(me,str);
			}
			if(sizeof(os=keys(o)))
			{
				str = "你获得了";
				for(i=0;i<sizeof(os);i++)
				{
					obj = new(os[i]);
					if(obj->query_amount()) obj->set_amount(o[os[i]]);
					str += obj->short();
					obj->move(me);
					if(i<(sizeof(os)-1)) str += "，";
					else str += "。\n";
				}
				tell_object(me,str);
			}
			tell_object(me,NOR"\n");
			step = 0;
		}
		me->set("afk/step",step);
	}
}
